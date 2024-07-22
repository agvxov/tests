#!/bin/bash

GITEA_USER="anon"
GITEA_PASS="parevtizedmoszkvater"
GITEA_ADDRESS="http://192.168.0.144:3000"
SOURCE_DIR="/var/lib/gitea/"

TOKEN_NAME="$(mktemp -u | cut -d '.' -f 2)"
echo "token name: $TOKEN_NAME"
TOKEN_VALUE=$(curl -H "Content-Type: application/json" --data '{"name":"'${TOKEN_NAME}'"}' -u ${GITEA_USER}:${GITEA_PASS} ${GITEA_ADDRESS}/api/v1/users/anon/tokens | jq -r .sha1)
echo "token value: $TOKEN_NAME"

for i in "SOURCE_DIR/"*; do
	curl -H "Authorization: token 64f04a799bd2fe3e0183826510b9254881e40160" --data '{"name":"'${i}'"}' ${GITEA_ADDRESS}/api/v1/user/repos
done
