let onlyIf = check =>
  Json.Decode.map(result =>
    check(result) ?
      result :
      raise(Json.Decode.DecodeError("Decode.onlyIf check did not pass."))
  );
