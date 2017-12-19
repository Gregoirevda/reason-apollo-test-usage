// graphql-tools combines a schema string with resolvers.
const {makeExecutableSchema} = require('graphql-tools');

let todos = [{
    id: "uuid-1",
    name: 'Todo 1'
  },
  {
    id: "uuid-2",
    name: 'Todo 2'
  },
  {
    id: "uuid-3",
    name: 'Todo 3'
}];

// Construct a schema, using GraphQL schema language
const typeDefs = `
	type Todo {
		name: String!
		id: ID!
	}

  type Query {
    todos(from: Int, limit: Int): [Todo]
  }
  
  type Mutation {
    deleteTodo(id: ID): Todo
  }
`;

// Provide resolver functions for your schema fields
const resolvers = {
  Query: {
    todos: (_,{from = 0, limit = 10}) => {
      console.log(`Query: from=${from}, limit=${limit}`);
      return todos
        .filter((_, index) => index >= from && index < limit);
    }
  },
  Mutation: {
    deleteTodo: (_, {id = `uuid-${todos.length}`}) => {
      console.log(`Mutation: id=${id}`);
      const deletedTodo = todos.find(todo => todo.id === id);
      if(!deletedTodo){
        throw new Error('Todo not found');
        return;
      }
      todos = todos.filter(todo => todo.id !== deletedTodo.id)
      return deletedTodo;
    }
  }
};

exports.schema = makeExecutableSchema({
  typeDefs,
  resolvers,
});

