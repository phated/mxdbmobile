type t = string;

type encodeResult = {
  cardHashes: list(string),
  checksum: int,
};

let sixtyfour = [|
  "A",
  "B",
  "C",
  "D",
  "E",
  "F",
  "G",
  "H",
  "I",
  "J",
  "K",
  "L",
  "M",
  "N",
  "O",
  "P",
  "Q",
  "R",
  "S",
  "T",
  "U",
  "V",
  "W",
  "X",
  "Y",
  "Z",
  "a",
  "b",
  "c",
  "d",
  "e",
  "f",
  "g",
  "h",
  "i",
  "j",
  "k",
  "l",
  "m",
  "n",
  "o",
  "p",
  "q",
  "r",
  "s",
  "t",
  "u",
  "v",
  "w",
  "x",
  "y",
  "z",
  "0",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "-",
  "_",
|];

let encodeQty = qty => (qty - 1) * 65536;

let encodeRarity = rarity =>
  /* TODO: Should this be a View in Rarity Component? */
  Card.Rarity.toInt(rarity) * 8192;

let encodeNumber = number => (Card.Number.toInt(number) - 1) * 32;

let encodeExpansion = expansion =>
  /* TODO: Should this be a View in expansion Component? */
  Card.Expansion.toInt(expansion) * 2;

let toBase64 = hashIdx => {
  let _ = ();
  /* let asBase64 = sixtyfour[hashIdx]; */
  /* Belt.Option.getWithDefault(asBase64, ""); */
  sixtyfour[hashIdx];
};

let encodeChecksum = value =>
  switch (value) {
  | "0" => 0
  | "1" => 1
  | "2" => 2
  | "3" => 3
  | "4" => 4
  | "5" => 5
  | "6" => 6
  | "7" => 7
  | "8" => 8
  | "9" => 9
  | _ => 0
  };

let floorToInt = value => int_of_float(floor(value));

let encodeCard = (result, card, qty) => {
  let encodedQty = encodeQty(qty);
  let rarity = Card.rarityGet(card)->encodeRarity;
  let number = Card.numberGet(card)->encodeNumber;
  let expansion = Card.expansionGet(card)->encodeExpansion;

  let hash = encodedQty + rarity + number + expansion;

  /* Checkbit is no longer checked */
  let checkbit = 0;

  let hashWithCheckbit = hash + checkbit;

  let sextet3 = hashWithCheckbit mod 64;

  let sextet2 =
    floorToInt(float_of_int(hashWithCheckbit - sextet3) /. 64.0) mod 64;

  let sextet1 =
    floorToInt(float_of_int(hashWithCheckbit - sextet2 - sextet3) /. 4096.0)
    mod 64;

  let encodedSextet1 = toBase64(sextet1);

  let encodedSextet2 = toBase64(sextet2);

  let encodedSextet3 = toBase64(sextet3);

  let checksum =
    encodeChecksum(encodedSextet1)
    + encodeChecksum(encodedSextet2)
    + encodeChecksum(encodedSextet3);

  let cardHash = encodedSextet1 ++ encodedSextet2 ++ encodedSextet3;

  {
    cardHashes: Belt.List.concat(result.cardHashes, [cardHash]),
    checksum: result.checksum + checksum,
  };
};

let emptyResult = encodedVersion => {
  cardHashes: [],
  checksum: encodeChecksum(encodedVersion),
};

let encode = deck => {
  let version = 0;

  let encodedVersion = toBase64(version);

  let result = emptyResult(encodedVersion);

  let encodeResult = Belt.Map.reduce(deck, result, encodeCard);

  let encodedDeck =
    encodedVersion ++ String.concat("", encodeResult.cardHashes);

  let base64Checksum = toBase64(encodeResult.checksum mod 64);

  let encoded = encodedDeck ++ base64Checksum;
  /* AiAASAhA */
  if (Belt.List.size(encodeResult.cardHashes) > 0) {
    Some(encoded);
  } else {
    None;
  };
};
