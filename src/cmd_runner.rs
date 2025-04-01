use std::process::{Command, Stdio};
use std::io::{Error, ErrorKind, Write};

use crate::traits::Runnable;

pub struct CMDRunner {
    cmd: String,
    args: Vec<String>,
    input: Option<String>,
}

impl Runnable for CMDRunner {
    fn run(&self) -> Result<String, std::io::Error> {
        let mut child = Command::new(&self.cmd)
            .args(&self.args)
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .spawn()?;
        if let Some(inp) = &self.input {
            if let Some(mut stdin) = child.stdin.take() {
                writeln!(stdin, "{}", inp)?;
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

impl CMDRunner {
    pub fn new(cmd: String, args: Vec<String>, input: Option<String>) -> Self {
        CMDRunner {
            cmd,
            args,
            input,
        }
    }
}
