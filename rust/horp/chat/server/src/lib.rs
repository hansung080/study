use std::collections::HashMap;
use std::io::{BufRead, BufReader, Write};
use std::net::{TcpListener, TcpStream};
use std::sync::mpsc;
use std::thread;
use common::message::Message;
use common::util::Pushed;

pub fn run(addr: &str) {
    let server = TcpListener::bind(addr).expect(&format!("failed to bind address {}", addr));
    server.set_nonblocking(false).expect("failed to set nonblocking for server");
    let mut clients = HashMap::<String, TcpStream>::new();
    let (tx, rx) = mpsc::channel::<(Message, Option<TcpStream>)>();
    println!("Chat server is running on {}.", addr);

    thread::spawn(move || loop {
        if let Ok((mut msg, client)) = rx.recv() {
            handle_message(&mut clients, &mut msg, client);
        }
    });

    loop {
        if let Ok((client, addr)) = server.accept() {
            client.set_nonblocking(false).expect("failed to set nonblocking for client");
            println!("accepted client: {}", addr);
            thread::spawn({
                let tx = mpsc::Sender::clone(&tx);
                move || recv_from(client, tx)
            });
        }
    }
}

fn recv_from(client: TcpStream, tx: mpsc::Sender<(Message, Option<TcpStream>)>) {
    let mut reader = BufReader::new(client.try_clone().unwrap());

    let mut json = String::new();
    if let Ok(n) = reader.read_line(&mut json) {
        println!("received message: {}", json.trim());
        if n > 0 {
            tx.send((Message::from_json(&json), Some(client))).unwrap();
        } else {
            println!("stream is closed.");
            return;
        }
    }

    loop {
        let mut json = String::new();
        if let Ok(n) = reader.read_line(&mut json) {
            println!("received message: {}", json.trim());
            if n > 0 {
                tx.send((Message::from_json(&json), None)).unwrap();
            } else {
                println!("stream is closed.");
                return;
            }
        }
    }
}

fn handle_message(clients: &mut HashMap<String, TcpStream>, msg: &mut Message, client: Option<TcpStream>) {
    match msg.kind {
        Message::KIND_REGISTER => if let Some(client) = client {
            handle_register_message(clients, msg, client);
        },
        Message::KIND_CHAT => handle_chat_message(clients, msg),
        Message::KIND_EXIT => handle_exit_message(clients, msg),
        unknown => println!("unknown message kind: {}", unknown),
    }
}

fn handle_register_message(clients: &mut HashMap<String, TcpStream>, msg: &mut Message, mut client: TcpStream) {
    if let None = clients.get(&msg.from) {
        send_to(&mut client, msg, &msg.from);
        clients.insert(msg.from.clone(), client);
        broadcast(clients, msg);
        println!("{} was registered and {} clients exist", msg.from, clients.len());
    } else {
        msg.error = format!("{} already exists", msg.from);
        send_to(&mut client, msg, &msg.from);
    }
}

fn handle_chat_message(clients: &mut HashMap<String, TcpStream>, msg: &mut Message) {
    if msg.to.len() == 0 {
        broadcast(clients, msg);
    } else {
        if let Some(client) = clients.get_mut(&msg.to) {
            send_to(client, msg, &msg.to);
        } else {
            if let Some(client) = clients.get_mut(&msg.from) {
                msg.error = format!("{} not found", msg.to);
                send_to(client, msg, &msg.from);
            } else {
                println!("failed to find both {} and {}", msg.to, msg.from);
            }
        }
    }
}

fn handle_exit_message(clients: &mut HashMap<String, TcpStream>, msg: &mut Message) {
    if let Some(client) = clients.get_mut(&msg.from) {
        send_to(client, msg, &msg.from);
        clients.remove(&msg.from);
        broadcast(clients, msg);
        println!("{} was removed and {} clients exist", msg.from, clients.len());
    } else {
        println!("failed to find {}", msg.from);
    }
}

fn send_to(client: &mut TcpStream, msg: &Message, id: &str) {
    let mut json = msg.to_json();
    println!("send to {}: {}", id, json);
    if let Err(e) = client.write_all(json.pushed('\n').as_bytes()) {
        println!("failed to send to: {}, caused by {}", json.trim(), e);
    }
}

fn broadcast(clients: &mut HashMap<String, TcpStream>, msg: &Message) {
    let json = msg.to_json().into_pushed('\n');
    let bytes = json.as_bytes();
    let mut sent = 0;
    for (id, client) in clients {
        if *id == msg.from {
            continue;
        }
        if let Err(e) = client.write_all(bytes) {
            println!("failed to broadcast: {}, caused by {}", json.trim(), e);
            continue;
        }
        sent += 1;
    }
    println!("broadcast to {} clients: {}", sent, json.trim());
}