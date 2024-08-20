use serde::{Deserialize, Serialize};
use std::default::Default;

// Config structure
#[derive(Debug, Serialize, Deserialize)]
pub struct Config {
    pub bookmarks: Vec<Bookmark>,
    pub runner: String,
    pub args: Vec<String>,
}

impl Default for Config {
    fn default() -> Self {
        Self {
            bookmarks: Vec::new(),
            runner: "fzf".to_owned(),
            args: Vec::new(),
        }
    }
}

impl Config {
    /// Finds a bookmark in the bookmarks list with a specific name.
    pub fn get_bookmark(&self, name: &str) -> Option<&Bookmark> {
        for i in &self.bookmarks {
            if i.name == name {
                return Some(i);
            };
        }
        None
    }
}

#[derive(Debug, Serialize, Deserialize, Default)]
pub struct Bookmark {
    pub name: String,
    pub address: String,
}
