COMPILER = "gcc"
SRC_PATH = "src"
SRC_FILE = "ProsesNative.c"
INC_PATH = "include"
LIB_PATH = "lib"
LIB = ["mruby", "m", "Ws2_32"]
RESULT_PATH = "build"
RESULT_FILE = "app.exe"
INC_PATH_COMMAND = "-I %s"
LIB_PATH_COMMAND = "-L %s"
LIB_COMMAND = "-l%s"
RESULT_COMMAND = "-o %s"
COMMAND = "%s %s %s %s %s %s"

def combine(option, *args)
	option % args
end

def runCommand(option, inc, libPath, lib, result)
	source = File.join(SRC_PATH, SRC_FILE)
	system(combine(option, COMPILER, source, inc, libPath, lib, result))
end

def runResult(exe)
	system(exe)
end

task :default do
	incPathCommand = combine(INC_PATH_COMMAND, INC_PATH)
	libPathCommand = combine(LIB_PATH_COMMAND, LIB_PATH)
	libCommand = LIB.collect { |l| combine(LIB_COMMAND, l) } .join(" ")
	resultCommand = combine(RESULT_COMMAND, File.join(RESULT_PATH, RESULT_FILE))

	if runCommand(COMMAND, incPathCommand, libPathCommand, libCommand, resultCommand)
		Dir.chdir(RESULT_PATH)
		runResult(RESULT_FILE)
	end
end