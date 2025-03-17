use std::process::{Command, Stdio};

fn main() {
}

fn open_file(url: &str) {
    let mut xdg = Command::new("xdg-open");
    xdg.arg(url);
    let spawning_result = xdg.spawn();
    if spawning_result.is_err() {
        println!("{:?}", spawning_result.unwrap_err());
        return;
    }
    let _ = spawning_result.unwrap().wait();
}

