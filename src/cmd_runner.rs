use crate::traits::Runnable;

pub struct CMDRunner {
    cmd: String,
    input: Option<String>,
    err: Option<String>
}

impl Runnable for CMDRunner {
    fn run(&self) -> Result<String, std::io::Error> {
        Err(std::io::Error::new(std::io::ErrorKind::Other, "Not implemented"))
    }
}

impl CMDRunner {
    pub fn new(cmd: String, input: Option<String>, err: Option<String>) -> Self {
        CMDRunner {cmd, input, err}
    }
}
