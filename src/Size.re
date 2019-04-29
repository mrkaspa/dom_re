type t =
  | S
  | M
  | L
  | XL;
let shirtSizeOfString = s =>
  switch (s) {
  | "S" => Some(S)
  | _ => None
  };

let price = s =>
  switch (s) {
  | S => 10.0
  | _ => 0.0
  };
