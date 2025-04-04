use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
/// A bookmark containing a name and a link
pub struct BookMark {
    pub name: String,
    pub link: String
}

impl PartialEq for BookMark {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name && self.link == other.link
    }
}

#[derive(Serialize, Deserialize, Debug, Clone)]
/// Configuration for webspeeddial
///
/// It contains the `runner` that is used to pick a `BookMark` and all the bookmarks
pub struct Config {
    runner: String,
    arguments: Vec<String>,
    bookmarks: Vec<BookMark>
}

impl Default for Config {
    /// Default settings for the `Config`
    fn default() -> Self {
        Config {
            runner: String::from("fzf"),
            arguments: vec![],
            bookmarks: vec![BookMark {name: String::from("Webspeeddial"), link: String::from("https://github.com/LarsZauberer/webspeeddial")}]
        }
    }
}

impl Config {
    /// Constructor for the Config
    pub fn new(runner: String, arguments: Vec<String>, bookmarks: Vec<BookMark>) -> Self {
        Config {runner, arguments, bookmarks}
    }

    /// Gets a bookmark by its name
    ///
    /// If there are multiple bookmarks with the same name, the first one is picked
    pub fn find_bookmark(&self, name: &str) -> Option<&BookMark> {
        let matches: Vec<&BookMark> = self.bookmarks.iter().filter(|x| x.name == name).collect();
        if !matches.is_empty() {
            Some(matches[0])
        } else {
            None
        }
    }

    pub fn get_runner(&self) -> &str {
        &self.runner
    }

    pub fn get_bookmarks(&self) -> &Vec<BookMark> {
        &self.bookmarks
    }

    pub fn get_arguments(&self) -> &Vec<String> {
        &self.arguments
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_find_bookmarks_normal_case() {
        let bma = BookMark {name: String::from("a"), link: String::from("b")};
        let bmb = BookMark {name: String::from("c"), link: String::from("d")};
        let bms = vec![bma, bmb];

        let cfg = Config {runner: String::from(""), arguments: vec![], bookmarks: bms};

        let search_result1 = cfg.find_bookmark(&cfg.bookmarks[0].name);
        let search_result2 = cfg.find_bookmark(&cfg.bookmarks[1].name);
        let search_result3 = cfg.find_bookmark("b");

        assert!(search_result1.is_some());
        assert!(search_result2.is_some());
        assert!(search_result3.is_none());

        assert_eq!(search_result1.unwrap(), &cfg.bookmarks[0]);
        assert_eq!(search_result2.unwrap(), &cfg.bookmarks[1]);
    }
}
