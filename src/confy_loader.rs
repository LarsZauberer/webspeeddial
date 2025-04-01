use crate::{config::Config, traits::ConfigLoader};

pub struct ConfyLoader {
    project: String,
    file_name: String
}

impl ConfigLoader for ConfyLoader {
    fn load(&self) -> Config {
        confy::load(&self.project, self.file_name.as_str()).unwrap_or_else(|_| {
            println!("Warning: Config file couldn't been read. Using default");
            Config::default()
        })
    }
}

impl ConfyLoader {
    pub fn new(project: String, file_name: String) -> Self {
        ConfyLoader {
            project, file_name
        }
    }
}
