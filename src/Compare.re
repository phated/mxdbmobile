let concat = comparators => {
  let rec cmp = (comparators, first, second) =>
    switch (comparators) {
    | [] => compare(first, second)
    | [run, ...rest] =>
      let result = run(first, second);
      if (result == 0) {
        cmp(rest, first, second);
      } else {
        result;
      };
    };

  cmp(comparators);
};

let by = (run, first, second) => compare(run(first), run(second));
