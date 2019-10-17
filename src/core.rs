pub fn dup(stack : &mut Vec<i32>) {
  if let Some(x) = stack.last().cloned() {
    stack.push(x);
  }
}

pub fn add(stack : &mut Vec<i32>) {
  if stack.len() >= 2 {
    let r = stack.pop().unwrap() + stack.pop().unwrap();
    stack.push(r);
  }
}

pub fn mul(stack : &mut Vec<i32>) {
  if stack.len() >= 2 {
    let r = stack.pop().unwrap() * stack.pop().unwrap();
    stack.push(r);
  }
}