use config::Config;
use traits::{ConfigLoader, Runnable};

pub mod cmd_runner;
pub mod config;
pub mod confy_loader;
pub mod traits;

pub fn run_app<T: Runnable, C: ConfigLoader>(runner: T, cfg_loader: C) {
    let cfg: Config = cfg_loader.load();

    let selection = match get_selection(&runner, &cfg) {
        Some(value) => value,
        None => return,
    };

    let bm_wrap = cfg.find_bookmark(&selection);
    if bm_wrap.is_none() {
        println!("No bookmark found!");
    }
    let bm = bm_wrap.unwrap();

    xdg_open(runner, bm);
}

fn xdg_open<T: Runnable>(runner: T, bm: &config::BookMark) {
    let res = runner.run("xdg-open", vec![bm.link.clone()], None);
    if res.is_err() {
        println!("xdg-open failed: {}", res.unwrap_err());
    }
}

fn get_selection<T: Runnable>(runner: &T, cfg: &Config) -> Option<String> {
    let selection_runner = runner.run(cfg.get_runner(), vec![], Some(cfg.get_bookmarks().iter().map(|x| x.name.clone()).collect()));
    if selection_runner.is_err() {
        println!("Runner failed! {}", selection_runner.unwrap_err());
        return None;
    }
    let mut selection = selection_runner.unwrap();
    selection = selection.replace("\n", "");
    println!("Selection: {}", selection);
    Some(selection)
}

#[cfg(test)]
mod tests {
    use config::BookMark;
    use mockall::predicate;
    use traits::{MockRunnable};

    use super::*;

    #[test]
    fn test_get_selection() {
        let mut r = MockRunnable::new();
        let bm = BookMark {name: String::from("hello"), link: String::from("world")};
        let cfg = Config::new(String::from("fzf"), vec![bm]);

        r.expect_run().with(predicate::eq("fzf"), predicate::eq(vec![]), predicate::eq(Some(vec![String::from("hello")]))).times(1).returning(|_, _, _| Ok(String::from("hello\n")));

        let output = get_selection(&r, &cfg);
        assert!(output.is_some());
        let out = output.unwrap();
        assert_eq!(out, String::from("hello"));
    }
}
