import subprocess
import unittest

class TestHardwareDriver(unittest.TestCase):
    EXECUTABLE = "./userHardware"

    def test_output(self):
        res = subprocess.run([self.EXECUTABLE], capture_output=True, text=True)
        print(f"Result: \n{res.stdout}")        
        # Begins with resume
        current_command = "HARDWARE_DEVICE_RESUME"

        prev_command = ""
        prev_result = ""

        for line in res.stdout.splitlines():
            if "HARDWARE_DEVICE_HALT" in line:
                prev_command = current_command
                current_command = "HARDWARE_DEVICE_HALT"
                
                prev_result = ""
                continue
            elif "HARDWARE_DEVICE_RESUME" in line:
                prev_command = current_command
                current_command = "HARDWARE_DEVICE_RESUME"
                
                continue
            elif prev_result == "":
                # This is the first output line
                prev_result = line
                continue
            
            # Can assume prev_result exists
            if current_command == "HARDWARE_DEVICE_RESUME" and prev_command != "HARDWARE_DEVICE_HALT":
                self.assertNotEqual(prev_result, line)
            elif current_command == "HARDWARE_DEVICE_HALT":
                self.assertEqual(prev_result, line)
            else:
                # if switching from halt to resume the first one should match
                self.assertEqual(prev_result, line)

                # Reset last command to continue current_command
                prev_command = ""
            
            prev_result = line 
        


if __name__ == "__main__":
    unittest.main()
    
