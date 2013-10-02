Pod::Spec.new do |s|
  s.name         = "AMError"
  s.version      = "0.0.1"
  s.summary      = "An enhanced NSError subclass."
  s.description  = <<-DESC
                   * Accessors for all common 'UserInfo' keys
                   * Adds a mutable subclasses, AMMutableError
                   * Easily add source (file, line) with provided macros
                   * Reads localizedDescriptions from strings tables
                   DESC
  s.homepage     = "https://github.com/amrox/AMError"
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author       = { "Andy Mroczkowski" => "andy@mrox.net" }
  s.ios.deployment_target = '6.1'
  s.osx.deployment_target = '10.8'
  s.source       = { :git => "https://github.com/amrox/AMError.git", :tag => "0.0.1" }
  s.source_files  = 'AMError/AMError.{h,m}'
  s.framework  = 'Foundation'
  s.requires_arc = true
end
