#include <fstream>
#include <memory>

class Printable
{
public:
	virtual ~Printable() = default;
	virtual std::string print() const = 0;	
};

class DataHTML : public Printable
{
public:
	DataHTML(std::string data) : data_(std::move(data)) {}
	std::string print() const override
	{
		return "<html>" + data_ + "<html/>";
	}
private:
	std::string data_;
};

class DataText : public Printable
{
public:
	DataText(std::string data) : data_(std::move(data)) {}
	std::string print() const override
	{
		return data_;
	}
private:
	std::string data_;
};

class DataJSON : public Printable
{
public:
	DataJSON(std::string data) : data_(std::move(data)) {}
	std::string print() const override
	{
		return "{ \"data\": \"" + data_ + "\"}";
	}
private:
	std::string data_;
};

void saveTo(std::ofstream &file, const Printable &printable)
{
	file << printable.print() << '\n';
}

int main()
{
	setlocale(LC_ALL, "RU");
	std::unique_ptr<Printable> html (new DataHTML("Тест_HTML"));
	std::unique_ptr<Printable> text (new DataText("Тест_Text"));
	std::unique_ptr<Printable> json (new DataJSON("Тест_JSON"));

	std::ofstream file("Тест.txt");
	if (file.is_open())
	{
		saveTo(file, *html);
		saveTo(file, *text);
		saveTo(file, *json);

		file.close();
	}

	return 0;
}