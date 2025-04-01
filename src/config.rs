use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug)]
pub struct BookMark {
    pub name: String,
    pub link: String
}

impl PartialEq for BookMark {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name && self.link == other.link
    }
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Config {
    runner: String,
    bookmarks: Vec<BookMark>
}

impl Default for Config {
    fn default() -> Self {
        Config {
            runner: String::from("fzf"),
            bookmarks: vec![BookMark {name: String::from("Webspeeddial"), link: String::from("https://github.com/LarsZauberer/webspeeddial")}]
        }
    }
}

impl Config {
    pub fn bookmarks_to_selection(&self) -> String {
        let mut selection_string: String = String::from("");
        for i in 0..self.bookmarks.len() {
            let bm = &self.bookmarks.get(i).expect("Out of bounds in bookmarks_to_selection");
            if i == self.bookmarks.len() - 1 {
                selection_string = selection_string + &bm.name;
            } else {
                selection_string = selection_string + &bm.name + "\n";
            }
        }
        selection_string
    }

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
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_bookmarks_to_selection_normal_case() {
        let bma = BookMark {name: String::from("a"), link: String::from("b")};
        let bmb = BookMark {name: String::from("c"), link: String::from("d")};
        let bms = vec![bma, bmb];

        let cfg = Config {runner: String::from(""), bookmarks: bms};

        assert_eq!(cfg.bookmarks_to_selection(), String::from("a\nc"));
    }

    #[test]
    fn test_find_bookmarks_normal_case() {
        let bma = BookMark {name: String::from("a"), link: String::from("b")};
        let bmb = BookMark {name: String::from("c"), link: String::from("d")};
        let bms = vec![bma, bmb];

        let cfg = Config {runner: String::from(""), bookmarks: bms};

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
