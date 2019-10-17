#[macro_use]
extern crate lazy_static;

mod core;
use std::io::{self, Write};
use std::collections::HashMap;

lazy_static! {
  static ref WORDS : HashMap<&'static str, fn(&mut Vec<i32>)> = {
    let mut map = HashMap::new();
    map.insert("dup", core::dup as fn(&mut Vec<i32>));
    map.insert("+", core::add as fn(&mut Vec<i32>));
    map.insert("*", core::mul as fn(&mut Vec<i32>));
    map
  };
}

fn main(){
  let mut data_stack : Vec<i32> = Vec::new();

  let mut buffer = String::new();
  loop {
    print!("ok> ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut buffer)
        .ok()
        .expect("Error reading input. Exiting.");
    if buffer.trim() == "exit" || buffer.trim() == "e" {
      break;
    }
    buffer.split_whitespace().for_each(|token| {
      match WORDS.get(token) {
        Some(fun) => fun(&mut data_stack),
        None => {
          match token.parse::<i32>() {
            Ok(num) => data_stack.push(num),
            Err(error) => panic!("Problem parsing token: {:?}", error)
          }
        }
      }
    });
    println!("data_stack : {:?}", data_stack);
    buffer.clear();
  }
}