use std::{
    char::from_u32,
    process::{Command, Stdio},
};

use web_speeddial::{Bookmark, Config};

fn main() {
    let config: Config =
        confy::load("web-speeddial", "config").expect("Couldn't read or write config file");

    let mut names: Vec<String> = Vec::with_capacity(config.bookmarks.len());

    // Create the string of all the bookmark selections
    for i in &config.bookmarks {
        names.push(i.name.to_owned());
    }
    let echo_string = names.join("\n");

    // Open the selector application
    // BUG: Needs some testing -> Hasn't been tested -> Likely to fail
    let selector_cmd = Command::new("sh")
        .arg("-c")
        .arg("echo")
        .arg(format!("$'{}'", echo_string))
        .arg("|")
        .arg(&config.runner)
        .args(&config.args)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .unwrap()
        .wait_with_output();
    if let Err(e) = selector_cmd {
        println!("Error: {:?}", e);
        panic!("Failed to select a speed dial option. Check runner and argument config")
    }
    let res = selector_cmd.unwrap();
    // Get selection string
    let output: String =
        String::from_utf8(res.stdout).expect("Failed to read answer from the selection");

    // Try find selection in the bookmarks
    let bookmark_option: Option<&Bookmark> = config.get_bookmark(&output);
    if bookmark_option.is_none() {
        panic!("Couldn't find selected bookmark: {}", output);
    }
    let bookmark: &Bookmark = bookmark_option.unwrap();

    // Xdg-open the address
    let open = Command::new("xdg-open").arg(&bookmark.address).output();
    if let Err(e) = open {
        println!("Error: {:?}", e);
        println!("Failed to open address {}", bookmark.address);
    }
}
