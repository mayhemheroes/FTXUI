FROM fuzzers/libfuzzer:12.0 as builder

RUN apt-get update
RUN apt install -y build-essential wget git clang cmake  automake autotools-dev  libtool zlib1g zlib1g-dev libexif-dev
ADD . /FTXUI
WORKDIR /FTXUI
RUN cmake .
RUN make
RUN make install
COPY fuzzers/fuzz_table.cpp .
RUN clang++ -I/usr/local/include -fsanitize=fuzzer,address fuzz_table.cpp -o fuzz_table /usr/local/lib/libftxui-screen.a /usr/local/lib/libftxui-dom.a /usr/local/lib/libftxui-component.a

FROM fuzzers/libfuzzer:12.0
COPY --from=builder /FTXUI/fuzz_table /
COPY --from=builder /usr/local/lib/* /usr/local/lib/

ENTRYPOINT []
CMD  ["/fuzz_table"]
