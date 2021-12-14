FROM seemongtan/make-gtest:latest
RUN apt install valgrind -y
COPY . /app
WORKDIR /app
CMD make ${TESTNAME}
