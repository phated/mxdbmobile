module Data = {
  [@bs.deriving abstract]
  type row('x, 'y) = {
    x: 'x,
    y: 'y,
    fill: string,
  };
};

module Legend = {
  [@bs.deriving abstract]
  type row('x) = {
    name: 'x,
    fill: string,
  };
};

let toLegendRow = row => {
  let name = Data.xGet(row);
  let fill = Data.fillGet(row);

  Legend.row(~name, ~fill);
};

type retainedProps('x, 'y) = {data: array(Data.row('x, 'y))};

let make = (~data, _children) => {
  let component = ReasonReact.statelessComponentWithRetainedProps("PieChart");

  let padding = Victory.padding(~top=55, ~bottom=0, ~left=0, ~right=0, ());
  let labels = data => {
    let y = Data.yGet(data);
    y === 0 ? "" : Printf.sprintf("%d", y);
  };

  let pieStyles = {
    "labels": {
      "fontWeight": "bold",
      "fill": Colors.white,
    },
    "data": {
      "fill": Data.fillGet,
    },
  };

  let legendStyles = {
    "data": {
      "fill": Legend.fillGet,
    },
  };

  let legend = Belt.Array.map(data, toLegendRow);

  {
    ...component,
    retainedProps: {
      data: data,
    },
    shouldUpdate: ({oldSelf, newSelf}) =>
      oldSelf.retainedProps.data !== newSelf.retainedProps.data,
    render: _self => {
      /* let dims = BsReactNative.Dimensions.get(`window);
         let halfWidth = dims##width / 2;

         let width = halfWidth - 10;
         let height = int_of_float(floor(float_of_int(halfWidth) *. 1.19)); */

      let height = 220;
      let width = 185;

      <Victory.Container height width responsive=false>
        <Victory.Legend
          standalone=false
          data=legend
          orientation="horizontal"
          itemsPerRow=2
          width
          symbolSpacer=10
          style=legendStyles
        />
        <Victory.Pie
          standalone=false
          data
          padding
          height
          width
          labelRadius=60
          labels
          style=pieStyles
        />
      </Victory.Container>;
    },
  };
};
