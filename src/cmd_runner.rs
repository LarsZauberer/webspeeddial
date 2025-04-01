use std::process::{Command, Stdio};
use std::io::{Error, ErrorKind, Write};

use crate::traits::Runnable;

pub struct CMDRunner {}

impl Runnable for CMDRunner {
    fn run(&self, cmd: &str, args: Vec<String>, input: Option<Vec<String>>) -> Result<String, std::io::Error> {
        let mut child = Command::new(cmd)
            .args(args)
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .spawn()?;
        if let Some(inp) = input {
            if let Some(mut stdin) = child.stdin.take() {
                for i in inp {
                    let _ = writeln!(stdin, "{}", i);
                }
                drop(stdin);
            };
        }
        let output_wrapped = child.wait_with_output()?;
        let output_decode_wrap = String::from_utf8(output_wrapped.stdout);
        if let Ok(out) = output_decode_wrap {
            Ok(out)
        } else {
            Err(Error::new(ErrorKind::InvalidInput, "Failed to read output of command"))
        }
    }
 }
