use std::io::{self, ErrorKind, Read, Write};

// Readers and Writers
//
//   Readers Which Implement the `std::io::Read` Trait
//
//     - std::io::Stdin: Created by std::io::stdin().
//     - std::fs::File:  Created by std::fs::File::open().
//     - std::net::TcpStream
//
//   Buffered Readers Which Implement the `std::io::BufRead` Trait
//
//     - std::io::StdinLock<'static>: Created by std::io::stdin().lock().
//     - std::io::BufReader<R>
//     - std::io::{Cursor<Vec<u8>>, Cursor<&[u8]>, Cursor<String>, Cursor<&str>}
//
//   Writers Which Implement the `std::io::Write` Trait
//
//     - std::io::Stdout: Created by std::io::stdout().
//     - std::io::Stderr: Created by std::io::stderr().
//     - std::fs::File:   Created by std::fs::File::create().
//     - std::net::TcpStream
//     - std::io::BufWriter<W>
//     - std::io::{Cursor<Vec<u8>>, Cursor<&mut [u8]>, Cursor<String>}
//     - Vec<u8>, &mut [u8]
//
//   Formatters Which Implement the `std::fmt::Write`
//
//     - String
//
//   Notes:
//     - The first argument to the `write!` macro can be a mutable reference to a value
//       whose type implements either `std::io::Write` or `std::fmt::Write`.
//

const DEFAULT_BUF_SIZE: usize = 8 * 1024;

pub fn copy<R, W>(reader: &mut R, writer: &mut W) -> io::Result<u64>
where
    R: ?Sized + Read,
    W: ?Sized + Write,
{
    let mut buf = [0; DEFAULT_BUF_SIZE];
    let mut written = 0;
    loop {
        let len = match reader.read(&mut buf) {
            Ok(0) => return Ok(written),
            Ok(len) => len,
            Err(ref e) if e.kind() == ErrorKind::Interrupted => continue,
            Err(e) => return Err(e),
        };
        writer.write_all(&buf[..len])?;
        written += len as u64;
    }
}
