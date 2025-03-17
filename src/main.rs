use serde::{Deserialize, Serialize};
use std::process::{Command, Stdio};

#[derive(Serialize, Deserialize, Debug, Default)]
struct Config {
    runner: String,
    bookmarks: Vec<BookMark>,
}

#[derive(Serialize, Deserialize, Debug)]
struct BookMark {
    name: String,
    link: String,
}

impl PartialEq for BookMark {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name
    }
}

fn main() {
    let config: Config = confy::load("webspeeddial", "bookmarks").unwrap();
    check_config_validity(&config);
}

fn check_config_validity(config: &Config) -> bool {
    has_duplicated::<BookMark>(&config.bookmarks)
}

fn has_duplicated<T: PartialEq>(arr: &[T]) -> bool {
    let n = arr.len();
    for i in 0..n {
        for e in (i+1)..n {
            if arr[i] == arr[e] {
                return true;
            }
        }
    }
    false
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

fn run_menu(data: &[String], runner: &str) -> Option<String> {
    // Echo Process
    let mut echo = Command::new("echo");
    echo.arg(join_str(data, "\n"));
    echo.stdout(Stdio::piped());
    let echo_spawn = echo.spawn();

    // Getting the Echo Process
    if echo_spawn.is_err() {
        println!("{:?}", echo_spawn.unwrap_err());
        return None;
    }
    let mut echo_out = echo_spawn.unwrap();
    let _ = echo_out.wait();

    // Creating the fuzzy search process
    let mut fzf = Command::new(runner);
    fzf.stdin(Stdio::from(echo_out.stdout.unwrap()));
    fzf.stdout(Stdio::piped());

    if let Ok(out) = fzf.spawn() {
        let waiting_result = out.wait_with_output();
        if let Ok(waited_output) = waiting_result {
            let decode_result = String::from_utf8(waited_output.stdout);
            decode_result.ok()
        } else {
            println!("{:?}", waiting_result.err());
            None
        }
    } else {
        println!("{:?}", fzf.output());
        None
    }
}

fn join_str(data: &[String], delimiter: &str) -> String {
    data.iter().fold(String::new(), |x, y| {
        if x.is_empty() {
            x + y
        } else {
            x + delimiter + y
        }
    })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_join_str() {
        let data: [String; 2] = [String::from("hello"), String::from("world")];
        assert_eq!(join_str(&data, "\n"), String::from("hello\nworld"));
    }
}
