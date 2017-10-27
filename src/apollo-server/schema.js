// graphql-tools combines a schema string with resolvers.
const {makeExecutableSchema} = require('graphql-tools');

// Construct a schema, using GraphQL schema language
const typeDefs = `
	type User {
		name: String
	}

  type Query {
    getUser: User
  }
`;

// Provide resolver functions for your schema fields
const resolvers = {
  Query: {
    getUser: () => {
      console.log('getting');
      return {
        name: 'Beautifull name coming from a GraphQL API'
      };
    }
  }
};

exports.schema = makeExecutableSchema({
  typeDefs,
  resolvers,
});

