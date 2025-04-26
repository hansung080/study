use std::io;
use std::io::Write;

pub struct Progresser {
    count: usize,
    limit: usize,
    display_num: usize,
    display_count: usize,
    display_times: usize,
}

impl Progresser {
    pub fn new(limit: usize, display_times: usize) -> Self {
        Progresser {
            count: 0,
            limit,
            display_num: limit / display_times,
            display_count: 1,
            display_times,
        }
    }

    pub fn progress(&mut self) {
        self.count += 1;
        if self.count == self.display_num * self.display_count && self.display_count < self.display_times {
            print!("{}% ", ((self.count as f64 / self.limit as f64) * 100.0) as usize);
            io::stdout().flush().unwrap();
            self.display_count += 1;
        }

        if self.count == self.limit {
            print!("100%");
            io::stdout().flush().unwrap();
            self.display_count += 1;
        }
    }

    pub fn reset(&mut self) {
        self.count = 0;
        self.display_num = self.limit / self.display_times;
        self.display_count = 1;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn progresser_test() {
        progresser_test_aux(200, 4);
        progresser_test_aux(199, 4);
        progresser_test_aux(201, 4);
    }

    fn progresser_test_aux(limit: usize, display_times: usize) {
        let mut p = Progresser::new(limit, display_times);
        print!("# progresser_test: ({limit}, {display_times}) => ");
        io::stdout().flush().unwrap();
        for _ in 0..limit {
            p.progress();
        }
        println!();
    }
}