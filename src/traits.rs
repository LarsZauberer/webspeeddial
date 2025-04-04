use mockall::automock;

use crate::config::Config;

#[automock]
/// It describes a struct that is tailored to a system that is able to run a command with certain arguments and an input
pub trait Runnable {
    /// Runs a command with given arguments and input
    ///
    /// It will return the output of the command or the io error.
    fn run(&self, cmd: &str, args: Vec<String>, input: Option<Vec<String>>) -> Result<String, std::io::Error>;
}

#[automock]
/// It describes a struct that is able to load a config
pub trait ConfigLoader {
    /// It loads the config from a source
    fn load(&self) -> Config;
}
