use webspeeddial::config::Config;
use webspeeddial::cmd_runner::CMDRunner;

fn main() {
    let cfg: Config = confy::load("webspeeddial", "config").unwrap_or_else(|_| {
        println!("Warning: Config file couldn't been read. Using default");
        Config::default()
    });

    let selector_string = cfg.bookmarks_to_selection();
    let selection_runner = CMDRunner::new(String::from(cfg.get_runner()), Some(cfg.bookmarks_to_selection()), Some(format!("Error: Failed to run cmd selector menu command {}", cfg.get_runner())));
}
