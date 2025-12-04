class CMDTEST_example < Cmdtest::Testcase
  def test_1
    cmd "example.out" do
      exit_zero
    end
  end
end
