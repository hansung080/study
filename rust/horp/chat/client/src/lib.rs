use std::io::{BufRead, BufReader, Write};
use std::net::TcpStream;
use std::{io, process, thread};
use common::message::Message;
use common::util::Pushed;

pub fn run(server_addr: &str) {
    let mut stream = TcpStream::connect(server_addr).expect(&format!("failed to connect to server {}", server_addr));
    stream.set_nonblocking(false).expect("failed to set nonblocking");

    let id = input("Your ID?");
    check_id(&id);

    thread::spawn({
        let stream = stream.try_clone().unwrap();
        let id = id.clone();
        move || recv_from(stream, id)
    });

    send_to(&mut stream, &Message::new(
        Message::KIND_REGISTER,
        id.clone(),
        "".to_string(),
        "".to_string()
    ));

    loop {
        let id = id.clone();
        let content = input("");
        let (cmd, content) = extract_command(content);
        match cmd.as_str() {
            Message::CMD_EXIT => send_to(&mut stream, &Message::new(
                Message::KIND_EXIT,
                id,
                "".to_string(),
                "".to_string(),
            )),
            _ => send_to(&mut stream, &Message::new(
                Message::KIND_CHAT,
                id,
                cmd,
                content,
            )),
        }
    }
}

fn recv_from(stream: TcpStream, id: String) {
    let mut reader = BufReader::new(stream);
    loop {
        let mut json = String::new();
        if let Ok(n) = reader.read_line(&mut json) {
            if n > 0 {
                handle_message(&Message::from_json(&json), &id);
            } else {
                println!("ERROR> stream is closed.");
                return;
            }
        }
    }
}

fn handle_message(msg: &Message, id: &str) {
    match msg.kind {
        Message::KIND_REGISTER => {
            if msg.error.len() == 0 {
                if msg.from == id {
                    println!("INFO> ID '{}' is available.", msg.from);
                } else {
                    println!("INFO> {} entered.", msg.from);
                }
            } else {
                println!("ERROR> {}", msg.error);
                process::exit(0);
            }
        },
        Message::KIND_CHAT => {
            if msg.error.len() == 0 {
                println!("{}> {}", msg.from, msg.content);
            } else {
                println!("ERROR> {}", msg.error);
            }
        },
        Message::KIND_EXIT => {
            if msg.error.len() == 0 {
                if msg.from == id {
                    println!("INFO> Bye, {}~!!", msg.from);
                    process::exit(0);
                } else {
                    println!("INFO> {} exited.", msg.from);
                }
            } else {
                println!("ERROR> {}", msg.error);
                process::exit(0);
            }
        },
        unknown => {
            println!("ERROR> unknown message kind: {}", unknown);
        },
    }
}

fn input(prompt: &str) -> String {
    if prompt.len() > 0 {
        print!("{} ", prompt);
        io::stdout().flush().expect("failed to flush to stdout");
    }
    let mut text = String::new();
    io::stdin().read_line(&mut text).expect("failed to read from stdin");
    String::from(text.trim())
}

fn check_id(id: &str) {
    let commands = [Message::CMD_EXIT];
    for cmd in commands {
        if cmd == id {
            println!("ERROR> ID cannot be one of {:?}", commands);
            process::exit(0);
        }
    }
}

fn extract_command(text: String) -> (String, String) {
    match text.chars().next() {
        Some(ch) if ch == '@' => {
            if let Some(pos) = text.chars().position(|ch| ch == ' ') {
                (String::from(&text[1..pos]), String::from((&text[pos..]).trim_start()))
            } else {
                (String::from(&text[1..]), String::from(""))
            }
        },
        _ => (String::from(""), text),
    }
}

fn send_to(stream: &mut TcpStream, msg: &Message) {
    let mut json = msg.to_json();
    stream.write_all(json.pushed('\n').as_bytes())
        .expect(&format!("failed to send message: {}", json.trim()));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn extract_command_test() {
        let cases = [
            ("", "", ""),
            ("Hi, friend!", "", "Hi, friend!"),
            ("Hi, alice@mail.com ~!!", "", "Hi, alice@mail.com ~!!"),
            ("@exit", "exit", ""),
            ("@exit ", "exit", ""),
            ("@exit  ", "exit", ""),
            ("@exit   ", "exit", ""),
            ("@ exit", "", "exit"),
            ("@  exit", "", "exit"),
            ("@   exit", "", "exit"),
            ("@AliceHi,friend!", "AliceHi,friend!", ""),
            ("@Alice Hi, friend!", "Alice", "Hi, friend!"),
            ("@Alice  Hi, friend!", "Alice", "Hi, friend!"),
            ("@Alice   Hi, friend!", "Alice", "Hi, friend!"),
            ("@ Alice Hi, friend!", "", "Alice Hi, friend!"),
            ("@  Alice Hi, friend!", "", "Alice Hi, friend!"),
            ("@   Alice Hi, friend!", "", "Alice Hi, friend!"),
        ];

        for (text_in, cmd, text_out) in cases {
            let text_in = text_in.to_string();
            let cmd = cmd.to_string();
            let text_out = text_out.to_string();
            assert_eq!((cmd, text_out), extract_command(text_in));
        }
    }
}