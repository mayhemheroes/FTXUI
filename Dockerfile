FROM fuzzers/libfuzzer:12.0

RUN apt-get update
RUN apt install -y build-essential wget git clang cmake  automake autotools-dev  libtool zlib1g zlib1g-dev libexif-dev
RUN git clone https://github.com/ArthurSonzogni/FTXUI.git
WORKDIR /FTXUI
RUN cmake .
RUN make
RUN make install
COPY fuzzers/fuzz.cpp .
RUN clang++ -I/usr/local/include -fsanitize=fuzzer,address fuzz.cpp -o /fuzz_table /usr/local/lib/libftxui-screen.a /usr/local/lib/libftxui-dom.a /usr/local/lib/libftxui-component.a


ENTRYPOINT []
CMD  ["/fuzz_table"]
