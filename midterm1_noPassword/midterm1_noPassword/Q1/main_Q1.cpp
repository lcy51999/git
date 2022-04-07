// Change FileNumber to 3 if you want more test datas.
#define FileNumber 1

// You shouldn't do anything in this file.

#include "Matrix.h"
#include <fstream>
#include <iomanip>

const vector<int> split(const string& str, const string& pattern) {
	vector<int> result;
	string::size_type begin, end;

	if (str.compare("(Not valid)") == 0)
	{
		return result;
	}

	end = str.find(pattern);
	begin = 0;

	while (end != string::npos) {
		if (end - begin != 0) {
			result.push_back(std::stoull(str.substr(begin, end - begin)));
		}
		begin = end + pattern.size();
		end = str.find(pattern, begin);
	}

	if (begin != str.length()) {
		result.push_back(std::stoull(str.substr(begin)));
	}
	return result;
}

bool Check(Matrix& Ma, vector<int>& ans)
{
	auto Fa = Ma.Flattern();
	for (size_t i = 0; i < ans.size(); i++)
		if (Fa[i] != ans[i])
			return false;
	return true;
}

void OutError(Matrix& Ma, vector<int>& ans, string whileDoing)
{
	cout << "While doing " << whileDoing << ", the answer should be: " << endl;
	for (size_t i = 0; i < ans.size(); i++)
		cout << ans[i] << ' ';
	cout << endl;

	cout << "But your answer is: " << endl;
	if (!Ma.isValid)
	{
		cout << "(Not valid)" << endl;
		return;
	}

	auto Fa = Ma.Flattern();
	for (size_t i = 0; i < Fa.size(); i++)
		cout << Fa[i] << ' ';
	cout << endl;
}

string fileName = "./input.txt";
string answer = "./answer.txt";
bool verbose = 1;

vector<float> score, total;
Matrix Ma, Mb;
void Run()
{
	ifstream FileInput(fileName);
	ifstream FileOutput(answer);
	if (!FileInput) {
		cout << "Invalid File." << endl;
		return;
	}

	string line;
	getline(FileInput, line);
	vector<int> vs = split(line, " ");
	vector<int> data = { vs.begin() + 2, vs.end() };
	Ma = Matrix(vs[0], vs[1], data);

	getline(FileInput, line);
	vector<int> vsb = split(line, " ");
	data = { vsb.begin() + 2, vsb.end() };
	Mb = Matrix(vsb[0], vsb[1], data);


	getline(FileOutput, line);
	vector<int> ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[0]++;
		if (Check(Ma, ans)) score[0] += Ma.isValid; else if (verbose) OutError(Ma, ans, "Constructing matrix A");
	}

	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[0]++;
		if (Check(Mb, ans)) score[0] += 1; else if (verbose) OutError(Mb, ans, "Constructing matrix B");
	}

	Matrix Mc;
	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[2]++;
		Mc = Matrix::Add(Ma, Mb);
		if (Check(Mc, ans)) score[2] += 1; else if (verbose) OutError(Mc, ans, "Add A with B");
	}

	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[1]++;
		Mc = Mb + Ma;
		if (Check(Mc, ans)) score[1] += 1; else if (verbose) OutError(Mc, ans, "Doing B + A");
	}

	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[3]++;
		Mc = Matrix::Minus(Ma, Mb);
		if (Check(Mc, ans)) score[3] += 1; else if (verbose) OutError(Mc, ans, "Minus A with B");
	}

	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[1]++;
		Mc = Mb - Ma;
		if (Check(Mc, ans)) score[1] += 1; else if (verbose) OutError(Mc, ans, "Doing B - A");
	}


	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[4]++;
		Mc = Matrix::Transpose(Ma);
		if (Check(Mc, ans)) score[4] += 1; else if (verbose) OutError(Mc, ans, "Transpose A");
	}

	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[4]++;
		Mc = Matrix::Transpose(Mb);
		if (Check(Mc, ans)) score[4] += 1; else if (verbose) OutError(Mc, ans, "Transpose B");
	}

	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[5]++;
		Mc = Matrix::Multiply(Ma, Mb);
		if (Check(Mc, ans)) score[5] += 1; else if (verbose) OutError(Mc, ans, "Multiply A with B");
	}

	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[5]++;
		Mc = Matrix::Multiply(Mb, Ma);
		if (Check(Mc, ans)) score[5] += 1; else if (verbose) OutError(Mc, ans, "Multiply B with A");
	}


	getline(FileOutput, line);
	ans = split(line, " ");
	if (ans.size() > 0)
	{
		total[6]++;
		Mc = Ma.Deepcopy();
		Ma = Matrix();
		if (Check(Mc, ans)) score[6] += 1; else if (verbose) OutError(Mc, ans, "A.Deepcopy");
		Ma = Mc;
	}

	FileInput.close();
	FileOutput.close();
}

int main()
{
	cout << "Print:" << endl;
	Matrix(2, 3, vector<int>{1, 2, 3, 2, 3, 4}).Print();

	score = { 0,0,0,0,0,0,0 };
	total = { 0,0,0,0,0,0,0 };
	for (size_t i = 0; i < FileNumber; i++)
	{
		fileName = "./testdata/input" + std::to_string(i) + ".txt";
		answer = "./testdata/answer" + std::to_string(i) + ".txt";

		Run();
	}

	cout << endl;
	string type[7] = { "Construct", "Overloading", "Add", "Minus", "Transpose", "Multiply", "DeepCopy" };
	for (size_t i = 0; i < 7; i++)
	{
		cout << setw(11) << type[i] << ": " << setw(2) << score[i] << "/" << setw(2) << total[i] << endl;
	}

}