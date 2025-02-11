const credentials = require('../fixtures/credentials');

describe('template spec', () => {
  it('passes', () => {
    cy.visit('https://demo.gitea.com/');

    // Sign in
    cy.contains(/sign in/i).click();

    cy.url().should('not.eq', 'https://demo.gitea.com/');

    cy.get('body').contains(/sign in with gitea\.com/i).click();

    cy.get('#user_name').type(credentials.username);
    cy.get('#password').type(credentials.password);

    cy.get('body').contains('button', /sign in/i).click();

    // Find the latest repo
    cy.get('body').contains(/explore/i).click();

    cy.get('.flex-list').find('.flex-item-title').eq(0).find('a').eq(1).click();

    // Star it
    cy.get('.repo-header').contains(/star/i).click();

    cy.contains(/unstar/i).should('be.visible');

    // Create an issue
    cy.get('.secondary-nav').contains(/issues/i).click();
    cy.contains(/new issue/i).click();

    cy.get('#issue_title').type('test issue');

    cy.contains(/create issue/i).click();

    cy.url().should('match', /\/issues\/\d+$/);
  })
})
