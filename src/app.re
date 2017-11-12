[@bs.module] external gql : ReasonApolloTypes.gql = "graphql-tag";

/* Describe the result type */
type todo = {. "name": string, "id": string};
type data = {. "todos": array(todo)};

/* Write graphql query passing a limit as variable */
let query = [@bs] gql({|
    query getTodos($limit: Int) {
      todos(limit: $limit) {
        id
        name
      }
    }
  |});

/* Optional: define variables for your query */
let variables = {
  "limit": 2
};


/* Pass the return type of the query to a module containing a type named `responseType` */
module Config = {
  type responseType = data;
  type variables = {. "limit": int};
};

/* You can now use `FetchTodos` as a JSX tag */
module FetchTodos = Apollo.Client(Config);

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {...component, render: (_self) =>
<FetchTodos query variables>
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
</FetchTodos>
};


