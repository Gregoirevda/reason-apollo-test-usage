external gql:ReasonApolloTypes.gql = "graphql-tag" [@@bs.module];

/* Describe the result type */
type getUser = Js.t {.name: string};
type data = Js.t {.getUser: getUser};

/* Write graphql query */
let query =
  gql {|
    query getUser {
      getUser {
        name
      }
    }
  |} [@bs];

/* Pass the above information to the Apollo Client */
module Config = {
  type responseType = data;
  let query = query;
};

/* You can now use it as a JSX call */
module FetchUserName = Apollo.Client Config;

let component = ReasonReact.statelessComponent "App";

let make _children => {
  ...component,
  render: fun _self =>
  <FetchUserName>
    (fun response => {
      let name = switch response##loading {
        | true => ""
        | false => response##data##getUser##name;

      };

      <div> (Utils.ste name) </div>
    })
  </FetchUserName>
};

