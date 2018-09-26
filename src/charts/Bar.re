module Data = {
  [@bs.deriving abstract]
  type row('x, 'y) = {
    x: 'x,
    y: 'y,
    fill: string,
  };
};

type retainedProps('x, 'y) = {data: array(array(Data.row('x, 'y)))};

let make = (~data, _children) => {
  let component = ReasonReact.statelessComponentWithRetainedProps("BarChart");

  let groupStyles = {
    "data": {
      "width": 8,
    },
  };

  let barStyles = {
    "data": {
      "fill": Data.fillGet,
    },
  };

  /* TODO: Props */
  let xAxisLabel = "Ranks";
  let xAxisTickValues = Belt.Array.range(1, 7);
  let xAxisStyles = {
    /* "axis": {
         "stroke": Colors.black,
       }, */
    "ticks": {
      size: 0,
    },
    "grid": {
      stroke: "none",
    },
    "axisLabel": {
      "padding": 24,
    },
  };
  let yAxisLabel = "Amount";
  let yAxisTickValues = Belt.Array.range(1, 3);
  let yAxisStyles = {
    /* "axis": {
         "stroke": Colors.black,
       }, */
    "axisLabel": {
      "padding": 24,
    },
  };

  let height = 220;
  let theme = Victory.Theme.material;
  let domain = Victory.domain(~x=[|1, 7|], ());
  let domainPadding =
    Victory.domainPadding(~x=[|20, 20|], ~y=[|20, 20|], ());

  {
    ...component,
    retainedProps: {
      data: data,
    },
    shouldUpdate: ({oldSelf, newSelf}) =>
      oldSelf.retainedProps.data !== newSelf.retainedProps.data,
    render: _self => {
      let dims = BsReactNative.Dimensions.get(`window);
      let width = dims##width - 10;

      <Victory.Container height width responsive=false>
        <Victory.Chart
          standalone=false theme height width domain domainPadding>
          <Victory.Axis
            dependentAxis=true
            style=yAxisStyles
            tickValues=yAxisTickValues
            label=yAxisLabel
          />
          <Victory.Group style=groupStyles offset=9>
            <Victory.Bar data={data[0]} style=barStyles />
            <Victory.Bar data={data[1]} style=barStyles />
            <Victory.Bar data={data[2]} style=barStyles />
            <Victory.Bar data={data[3]} style=barStyles />
          </Victory.Group>
          <Victory.Axis
            style=xAxisStyles
            tickValues=xAxisTickValues
            label=xAxisLabel
          />
        </Victory.Chart>
      </Victory.Container>;
    },
  };
};
