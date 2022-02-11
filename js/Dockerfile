#To build (Git Bash): docker build -t js .
#To run: docker run -v "$PWD:/app" -p 8080:8080 -t js

FROM node:14-alpine
RUN apk add --no-cache python2 g++ make
RUN mkdir /app
WORKDIR /app
RUN yarn global add http-server
RUN yarn global add mocha
EXPOSE 8080
CMD ["/bin/sh","-c","yarn install --check-files && node_modules/.bin/http-server"]