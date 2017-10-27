/* TODO: delete */
type getUser = Js.t {.name: string};
type data = Js.t {.getUser: getUser};
external gql:ReasonApolloTypes.gql = "graphql-tag" [@@bs.module];
external cast : string => Js.t {.data: data} = "%identity";

let component = ReasonReact.statelessComponent "App";

let query =
  gql {|
    query getUser {
      getUser {
        name
      }
    }
  |} [@bs];

let make _children => {
  ...component,
  render: fun _self =>
  <Apollo query>
    (fun response => {
      let name = switch response##loading {
        | true => ""
        | false => {
          let resp = cast response##data;
          let name = resp##data##getUser##name;
          name;
        }
      };

      <div> (Utils.ste name) </div>
    })
  </Apollo>
};
