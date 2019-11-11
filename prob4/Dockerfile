FROM node:10

RUN mkdir -p /var/ctf
COPY flag /var/ctf/
RUN chmod 444 /var/ctf/flag

# ======Build and run your service======
ADD /src /src
WORKDIR /src
COPY src/package*.json ./
RUN npm install
COPY src .
EXPOSE 8080
CMD [ "node", "server.js" ]

