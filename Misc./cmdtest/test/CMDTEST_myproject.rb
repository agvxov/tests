require 'fileutils'

class CMDTEST_example < Cmdtest::Testcase

  def test_1
    cmd "program.out" do
      exit_status 17
    end
  end

  def test_2
    arg_file = ENV['ORIGIN'] + "/debug/testfile.txt"
    cmd "program2.out " + arg_file do
    end
  end

end
