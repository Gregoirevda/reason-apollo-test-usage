// graphql-tools combines a schema string with resolvers.
const {makeExecutableSchema} = require('graphql-tools');

// Construct a schema, using GraphQL schema language
const typeDefs = `
	type Todo {
		name: String!
		id: ID!
	}

  type Query {
    todos: [Todo]
  }
`;

// Provide resolver functions for your schema fields
const resolvers = {
  Query: {
    todos: () => {
      console.log('getting');
      return [{
        id: "uuid-1",
        name: 'Todo 1'
      },
      {
        id: "uuid-2",
        name: 'Todo 2'
      }]
    }
  }
};

exports.schema = makeExecutableSchema({
  typeDefs,
  resolvers,
});

