[@bs.module] external gql : ReasonApolloTypes.gql = "graphql-tag";

/* Write graphql query passing a limit as variable */
let query = [@bs] gql({|
  query getTodos($from: Int, $limit: Int) {
    todos(from: $from, limit: $limit) {
      id
      name
    }
  }
|});

/* Describe the result type */
type todo = {. "name": string, "id": string};
type data = {. "todos": array(todo)};
type response = data;

/* Optional: Define the type of variables you give
   We also have a `from` variable coming from the props
 */
type variables = {. "limit": int, "from": int};
