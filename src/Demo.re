open Belt;

module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

let calcButton = Doc.getElementById("calculate", D.document);

let getValue = element =>
  element
  ->Option.map(Elem.unsafeAsHtmlElement)
  ->Option.map(D.HtmlElement.value);

let toInt = s =>
  switch (int_of_string(s)) {
  | result => Some(result)
  | exception (Failure(_)) => None
  };

let calculate = _elem => {
  let quantity =
    getValue(Doc.getElementById("quantity", D.document))
    ->Option.flatMap(_, toInt);

  let unitPrice =
    getValue(Doc.getElementById("size", D.document))
    ->Option.flatMap(_, Size.shirtSizeOfString)
    ->Option.map(_, Size.price);

  let totalPrice =
    switch (unitPrice, quantity) {
    | (Some(uPrice), Some(qty)) => Some(uPrice *. float_of_int(qty))
    | (_, _) => None
    };

  let priceString =
    switch (totalPrice) {
    | Some(total) => Js.Float.toFixedWithPrecision(total, ~digits=2)
    | None => ""
    };

  Js.log("Price = " ++ priceString);

  Doc.getElementById("price", D.document)
  ->Option.map(_, Elem.setInnerText(_, priceString))
  |> ignore;
};

calcButton->Option.map(elem =>
  D.EventTarget.addEventListener(
    "click",
    calculate,
    Elem.asEventTarget(elem),
  )
)
|> ignore;
