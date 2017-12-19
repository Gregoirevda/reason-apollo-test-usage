[@bs.module] external gql : ReasonApolloTypes.gql = "graphql-tag";

/* Write graphql query passing a limit as variable */
let mutation = [@bs] gql({|
  mutation deleteTodo($id: ID!) {
    deleteTodo(id: $id) {
      id
      name
    }
  }
|});

/* Describe the result type */
type todo = {. "name": string, "id": string};
type data = {. "deleteTodo": todo};
type response = data;

/* Optional: Define the type of variables you give
   We also have a `from` variable coming from the props
 */
type variables = {.
  "id": string
};
