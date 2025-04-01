use webspeeddial::cmd_runner::CMDRunner;
use webspeeddial::confy_loader::ConfyLoader;
use webspeeddial::run_app;

fn main() {
    run_app(CMDRunner {}, ConfyLoader::new(String::from("webspeeddial"), String::from("config")));
}
