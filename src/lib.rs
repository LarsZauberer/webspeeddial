use config::Config;
use traits::{ConfigLoader, Runnable};

pub mod cmd_runner;
pub mod config;
pub mod confy_loader;
pub mod traits;

pub fn run_app<T: Runnable, C: ConfigLoader>(runner: T, cfg_loader: C) {
    let cfg: Config = cfg_loader.load();

    let selection_runner = runner.run(cfg.get_runner(), vec![], Some(cfg.get_bookmarks().iter().map(|x| x.name.clone()).collect()));

    if selection_runner.is_err() {
        println!("Runner failed! {}", selection_runner.unwrap_err());
        return;
    }
    let mut selection = selection_runner.unwrap();
    selection = selection.replace("\n", "");
    println!("Selection: {}", selection);

    let bm_wrap = cfg.find_bookmark(&selection);
    if bm_wrap.is_none() {
        println!("No bookmark found!");
    }
    let bm = bm_wrap.unwrap();

    let res = runner.run("xdg-open", vec![bm.link.clone()], None);
    if res.is_err() {
        println!("xdg-open failed: {}", res.unwrap_err());
    }
}
