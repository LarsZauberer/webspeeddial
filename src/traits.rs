use mockall::automock;

#[automock]
pub trait Runnable {
    fn run(&self) -> Result<String, std::io::Error>;
}
