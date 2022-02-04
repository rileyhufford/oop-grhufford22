#To build (Git Bash): docker build -t js .
#To run: docker run -v "$PWD:/app" -p 8080:8080 -t js

FROM node:12-alpine
RUN apk add --no-cache python2 g++ make
RUN mkdir /app
WORKDIR /app
RUN yarn global add http-server
EXPOSE 8080
CMD ["http-server"]