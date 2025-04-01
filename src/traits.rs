use mockall::automock;

use crate::config::Config;

#[automock]
pub trait Runnable {
    fn run(&self, cmd: &str, args: Vec<String>, input: Option<Vec<String>>) -> Result<String, std::io::Error>;
}

#[automock]
pub trait ConfigLoader {
    fn load(&self) -> Config;
}
