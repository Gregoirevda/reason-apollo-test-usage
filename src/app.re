[@bs.module] external gql : ReasonApolloTypes.gql = "graphql-tag";

/* Describe the result type */
type todo = {. "name": string, "id": string};

type data = {. "todos": array(todo)};

/* Write graphql query */
let query = [@bs] gql({|
    query getTodos {
      todos {
        id
        name
      }
    }
  |});

/* Pass the above information to the Apollo Client */
module Config = {
  type responseType = data;
  let query = query;
};

/* You can now use it as a JSX call */
module FetchUserName = Apollo.Client(Config);

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {...component, render: (_self) =>
<FetchUserName>
  ((response) => {
    switch response##loading {
       | true => <div> (Utils.ste("Loading")) </div>
       | false => {
        <div>
        (
          ReasonReact.arrayToElement(
            Array.map(((todo) => <div key=(todo##id)> (Utils.ste(todo##name))</div>), response##data##todos)
          )
        )
        </div>
       }
    };
  })
</FetchUserName>
};
