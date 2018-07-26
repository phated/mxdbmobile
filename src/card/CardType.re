type t =
  | Character
  | Event
  | Battle;

let toInt = cardType =>
  switch (cardType) {
  | Character => 0
  | Event => 1
  | Battle => 2
  };
