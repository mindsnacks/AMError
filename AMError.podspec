Pod::Spec.new do |s|
  s.name         = "AMError"
  s.version      = "0.0.1"
  s.summary      = "A short description of AMError."
  s.description  = <<-DESC
                   A longer description of AMError in Markdown format.

                   * Think: Why did you write this? What is the focus? What does it do?
                   * CocoaPods will be using this to generate tags, and improve search results.
                   * Try to keep it short, snappy and to the point.
                   * Finally, don't worry about the indent, CocoaPods strips it!
                   DESC
  s.homepage     = "https://github.com/amrox/AMError"
  s.license  = { :type => 'MIT', :file => 'LICENSE' }
  s.author       = { "Andy Mroczkowski" => "andy@mrox.net" }
  s.ios.deployment_target = '6.0'
  s.osx.deployment_target = '10.7'
  s.source       = { :git => "https://github.com/amrox/AMError.git", :tag => "0.0.1" }
  s.source_files  = 'AMError/AMError.{h,m}'
  s.public_header_files = 'AMError/AMError.h'
  s.framework  = 'Foundation'
  s.requires_arc = true
end
