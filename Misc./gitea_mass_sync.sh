#!/bin/bash

GITEA_USER="anon"
GITEA_PASS="--"
GITEA_ADDRESS="192.168.0.144:3000"
SOURCE_DIR="/var/lib/gitea/data/gitea-repositories/${GITEA_USER}/"

TOKEN_NAME="$(mktemp -u | cut -d '.' -f 2)"
echo "token name: '$TOKEN_NAME'"
# TOKEN_VALUE=$(curl -H "Content-Type: application/json" --data '{"name":"'${TOKEN_NAME}'", "scopes": ["repo"]}' -u ${GITEA_USER}:${GITEA_PASS} http://${GITEA_ADDRESS}/api/v1/users/${GITEA_USER}/tokens | jq -r .sha1)
TOKEN_VALUE='--'
echo "token value: '$TOKEN_VALUE'"

for i in "$SOURCE_DIR/"*; do
	REPO_NAME=$(basename -s .git "$i")
	echo "	Repo: ${REPO_NAME}"
	#curl -X 'POST' \
	#	"http://192.168.0.144:3000/api/v1/repos/${GITEA_USER}/${REPO_NAME}/push_mirrors" \
	#	-H "Authorization: token ${TOKEN_VALUE}" \
	#	-H 'Content-Type: application/json' \
	#	-d '{
	#		"interval": "0",
	#		"remote_address": "'"https://github.com/agvxov/${REPO_NAME}.git"'",
	#		"remote_password": "--",
	#		"remote_username": "agvxov",
	#		"sync_on_commit": true
	#	}'
	curl -X 'POST' \
		-H "Authorization: token ${TOKEN_VALUE}" \
		"http://192.168.0.144:3000/api/v1/repos/${GITEA_USER}/${REPO_NAME}/push_mirrors-sync"
done

