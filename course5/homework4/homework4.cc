#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>

struct flush_t {
        const char* value;

        flush_t(const char* value)
        {
                this->value = value;
        }
};


class Stream {
public:
        Stream(FILE* fp)
        {
                this->fp = fp;
        }

        Stream(const char* filename)
        {
                fp = std::fopen(filename, "w");
                this->filename = filename;
        }

        Stream(const std::string& filename)
        {
                Stream(filename.c_str());
        }

        Stream(const Stream& other) = delete;

        ~Stream()
        {
                if (filename != nullptr) {
                        std::fclose(fp);
                }
        }

        const Stream& operator<<(int value) const
        {
                std::fprintf(fp, "%d", value);
                return *this;
        }

        const Stream& operator<<(const char* value) const
        {
                std::fprintf(fp, "%s", value);
                return *this;
        }

        const Stream& operator<<(const std::string& value) const
        {
                *this << value.c_str();
                return *this;
        }

        const Stream& operator<<(flush_t value) const
        {
                *this << value.value;
                std::fflush(fp);
                return *this;
        }

        const Stream& operator<<(double value) const
        {
                std::fprintf(fp, "%f", value);
                return *this;
        }

        const Stream& operator<<(unsigned int value) const
        {
                std::fprintf(fp, "%u", value);
                return *this;
        }

        const Stream& operator<<(bool value) const
        {
                if (value) {
                        std::fprintf(fp, "true");
                } else {
                        std::fprintf(fp, "false");
                }
                return *this;
        }

private:
        std::FILE* fp;
        const char* filename = nullptr;
};


flush_t Endl("\n");
Stream Cout(stdout);

int main(int, char**)
{
        Stream s("output.txt");
        std::string w = "World!";
        s << "Hello, " << w;

        Cout << "2 + 2 = " << 2 + 2 << Endl;
        Cout << "3.5 + 3.5 = " << 3.5 + 3.5 << Endl;
        Cout << "1 == 1 = " << (1 == 1) << Endl;

        return 0;
}