use webspeeddial::config::Config;
use webspeeddial::cmd_runner::CMDRunner;
use webspeeddial::traits::Runnable;

fn main() {
    let cfg: Config = confy::load("webspeeddial", "config").unwrap_or_else(|_| {
        println!("Warning: Config file couldn't been read. Using default");
        Config::default()
    });

    // Select bookmark
    let selection_runner = CMDRunner::new(String::from(cfg.get_runner()), vec![], Some(cfg.get_bookmarks().iter().map(|x| x.name.clone()).collect()));
    let out_wrap = selection_runner.run();
    let Ok(mut out) = out_wrap else {
        let err = out_wrap.unwrap_err();
        println!("Runner failed: {}", err);
        panic!();
    };

    out = out.replace("\n", "");
    println!("Selected Bookmark: {}", out);

    // Find bookmark
    let bm_wrap = cfg.find_bookmark(&out);
    let Some(bm) = bm_wrap else {
        println!("Bookmark not found in config");
        panic!();
    };
    let xdg_string = String::from("xdg-open");
    let xdg_runner = CMDRunner::new(xdg_string, vec![bm.link.clone()], None);
    let _ = xdg_runner.run();
}
